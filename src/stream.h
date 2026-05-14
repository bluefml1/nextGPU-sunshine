/**
 * @file src/stream.h
 * @brief Declarations for the streaming protocols.
 */
#pragma once

// standard includes
#include <cstdint>
#include <optional>
#include <utility>

// lib includes
#include <boost/asio.hpp>

// local includes
#include "audio.h"
#include "crypto.h"
#include "video.h"

namespace stream {
  constexpr auto VIDEO_STREAM_PORT = 9;
  constexpr auto CONTROL_PORT = 10;
  constexpr auto AUDIO_STREAM_PORT = 11;

  struct session_t;

  struct config_t {
    audio::config_t audio;
    video::config_t monitor;

    int packetsize;
    int minRequiredFecPackets;
    int mlFeatureFlags;
    int controlProtocolType;
    int audioQosType;
    int videoQosType;

    uint32_t encryptionFlagsEnabled;

    std::optional<int> gcmap;
  };

  namespace session {
    enum class state_e : int {
      STOPPED,  ///< The session is stopped
      STOPPING,  ///< The session is stopping
      STARTING,  ///< The session is starting
      RUNNING,  ///< The session is running
    };

    std::shared_ptr<session_t> alloc(config_t &config, rtsp_stream::launch_session_t &launch_session);
    int start(session_t &session, const std::string &addr_string);
    void stop(session_t &session);
    void join(session_t &session);
    state_e state(session_t &session);
  }  // namespace session

  /**
   * @brief Fork-only HTTP hook (nextGPU / Moonlight web): enqueue a realtime video target bitrate (kbps).
   * @details Loopback-only unless relaxed by deployment. Optional env `SUNSHINE_BITRATE_TOKEN` must match header
   *          `X-Sunshine-Bitrate-Token` when set. Not upstream LizardByte behavior.
   * @return HTTP-style status: 200, 400, 401, 403, 404, 409, 503.
   */
  int ml_stream_bitrate_http_post(
    const boost::asio::ip::address &remote,
    const std::optional<std::string> &x_sunshine_bitrate_token,
    std::uint32_t requested_kbps,
    std::uint32_t *applied_kbps_out);

  /** `session_opaque` is `stream::session_t*` from the video pipeline. Returns 0 if null. */
  std::uint32_t ml_launch_session_id_for_opaque_session(void *session_opaque);

  /** `session_opaque` is `stream::session_t*` from the video pipeline. */
  std::uint32_t ml_clamp_target_bitrate_kbps_for_running_session(void *session_opaque, std::uint32_t requested_kbps);

  /** After host encoder accepts a new target bitrate, sync monitor + ABR ceiling. */
  void ml_sync_session_after_bitrate_reconfigure(void *session_opaque, std::uint32_t applied_kbps);
}  // namespace stream
