<script setup>
import { computed, ref } from 'vue'
import {
  Info,
  TriangleAlert,
} from 'lucide-vue-next'
import Checkbox from "../../Checkbox.vue";

const props = defineProps([
  'platform',
  'config'
])

const defaultMoonlightPort = 47989

const config = ref(props.config)
const effectivePort = computed(() => +config.value?.port ?? defaultMoonlightPort)
</script>

<template>
  <div id="network" class="config-page">
    <!-- UPnP -->
    <Checkbox class="mb-3"
              id="upnp"
              locale-prefix="config"
              v-model="config.upnp"
              default="false"
    ></Checkbox>

    <!-- Address family -->
    <div class="mb-3">
      <label for="address_family" class="form-label">{{ $t('config.address_family') }}</label>
      <select id="address_family" class="form-select" v-model="config.address_family">
        <option value="ipv4">{{ $t('config.address_family_ipv4') }}</option>
        <option value="both">{{ $t('config.address_family_both') }}</option>
      </select>
      <div class="form-text">{{ $t('config.address_family_desc') }}</div>
    </div>

    <!-- Bind address -->
    <div class="mb-3">
      <label for="bind_address" class="form-label">{{ $t('config.bind_address') }}</label>
      <input type="text" class="form-control" id="bind_address" v-model="config.bind_address" />
      <div class="form-text">{{ $t('config.bind_address_desc') }}</div>
    </div>

    <!-- Port family -->
    <div class="mb-3">
      <label for="port" class="form-label">{{ $t('config.port') }}</label>
      <input type="number" min="1029" max="65514" class="form-control" id="port" :placeholder="defaultMoonlightPort"
             v-model="config.port" />
      <div class="form-text">{{ $t('config.port_desc') }}</div>
      <!-- Add warning if any port is less than 1024 -->
      <div class="alert alert-danger" v-if="(+effectivePort - 5) < 1024">
        <TriangleAlert :size="20" /> {{ $t('config.port_alert_1') }}
      </div>
      <!-- Add warning if any port is above 65535 -->
      <div class="alert alert-danger" v-if="(+effectivePort + 21) > 65535">
        <TriangleAlert :size="20" /> {{ $t('config.port_alert_2') }}
      </div>
      <!-- Create a port table for the various ports needed by Sunshine -->
      <table class="table">
        <thead>
        <tr>
          <th scope="col">{{ $t('config.port_protocol') }}</th>
          <th scope="col">{{ $t('config.port_port') }}</th>
          <th scope="col">{{ $t('config.port_note') }}</th>
        </tr>
        </thead>
        <tbody>
        <tr>
          <!-- HTTPS -->
          <td>{{ $t('config.port_tcp') }}</td>
          <td>{{+effectivePort - 5}}</td>
          <td></td>
        </tr>
        <tr>
          <!-- HTTP -->
          <td>{{ $t('config.port_tcp') }}</td>
          <td>{{+effectivePort}}</td>
          <td>
            <div class="alert alert-primary" role="alert" v-if="+effectivePort !== defaultMoonlightPort">
              <Info :size="20" /> {{ $t('config.port_http_port_note') }}
            </div>
          </td>
        </tr>
        <tr>
          <!-- Web UI -->
          <td>{{ $t('config.port_tcp') }}</td>
          <td>{{+effectivePort + 1}}</td>
          <td>{{ $t('config.port_web_ui') }}</td>
        </tr>
        <tr>
          <!-- RTSP -->
          <td>{{ $t('config.port_tcp') }}</td>
          <td>{{+effectivePort + 21}}</td>
          <td></td>
        </tr>
        <tr>
          <!-- Video, Control, Audio -->
          <td>{{ $t('config.port_udp') }}</td>
          <td>{{+effectivePort + 9}} - {{+effectivePort + 11}}</td>
          <td></td>
        </tr>
        <!--            <tr>-->
        <!--              &lt;!&ndash; Mic &ndash;&gt;-->
        <!--              <td>UDP</td>-->
        <!--              <td>{{+effectivePort + 13}}</td>-->
        <!--              <td></td>-->
        <!--            </tr>-->
        </tbody>
      </table>
      <!-- add warning about exposing web ui to the internet -->
      <div class="alert alert-warning" v-if="config.origin_web_ui_allowed === 'wan'">
        <TriangleAlert :size="20" /> {{ $t('config.port_warning') }}
      </div>
    </div>

    <!-- Origin Web UI Allowed -->
    <div class="mb-3">
      <label for="origin_web_ui_allowed" class="form-label">{{ $t('config.origin_web_ui_allowed') }}</label>
      <select id="origin_web_ui_allowed" class="form-select" v-model="config.origin_web_ui_allowed">
        <option value="pc">{{ $t('config.origin_web_ui_allowed_pc') }}</option>
        <option value="lan">{{ $t('config.origin_web_ui_allowed_lan') }}</option>
        <option value="wan">{{ $t('config.origin_web_ui_allowed_wan') }}</option>
      </select>
      <div class="form-text">{{ $t('config.origin_web_ui_allowed_desc') }}</div>
    </div>

    <!-- CSRF Allowed Origins -->
    <div class="mb-3">
      <label for="csrf_allowed_origins" class="form-label">{{ $t('config.csrf_allowed_origins') }}</label>
      <input type="text"
             class="form-control"
             id="csrf_allowed_origins"
             v-model="config.csrf_allowed_origins" />
      <div class="form-text">{{ $t('config.csrf_allowed_origins_desc') }}</div>
    </div>

    <!-- External IP -->
    <div class="mb-3">
      <label for="external_ip" class="form-label">{{ $t('config.external_ip') }}</label>
      <input type="text" class="form-control" id="external_ip" placeholder="123.456.789.12" v-model="config.external_ip" />
      <div class="form-text">{{ $t('config.external_ip_desc') }}</div>
    </div>

    <!-- LAN Encryption Mode -->
    <div class="mb-3">
      <label for="lan_encryption_mode" class="form-label">{{ $t('config.lan_encryption_mode') }}</label>
      <select id="lan_encryption_mode" class="form-select" v-model="config.lan_encryption_mode">
        <option value="0">{{ $t('_common.disabled_def') }}</option>
        <option value="1">{{ $t('config.lan_encryption_mode_1') }}</option>
        <option value="2">{{ $t('config.lan_encryption_mode_2') }}</option>
      </select>
      <div class="form-text">{{ $t('config.lan_encryption_mode_desc') }}</div>
    </div>

    <!-- WAN Encryption Mode -->
    <div class="mb-3">
      <label for="wan_encryption_mode" class="form-label">{{ $t('config.wan_encryption_mode') }}</label>
      <select id="wan_encryption_mode" class="form-select" v-model="config.wan_encryption_mode">
        <option value="0">{{ $t('_common.disabled') }}</option>
        <option value="1">{{ $t('config.wan_encryption_mode_1') }}</option>
        <option value="2">{{ $t('config.wan_encryption_mode_2') }}</option>
      </select>
      <div class="form-text">{{ $t('config.wan_encryption_mode_desc') }}</div>
    </div>

    <!-- Ping Timeout -->
    <div class="mb-3">
      <label for="ping_timeout" class="form-label">{{ $t('config.ping_timeout') }}</label>
      <input type="text" class="form-control" id="ping_timeout" placeholder="10000" v-model="config.ping_timeout" />
      <div class="form-text">{{ $t('config.ping_timeout_desc') }}</div>
    </div>

    <!-- Adaptive Bitrate -->
    <Checkbox class="mb-3"
              id="abr_enable"
              locale-prefix="config"
              v-model="config.abr_enable"
              default="disabled"
    ></Checkbox>

    <div v-if="config.abr_enable === 'enabled'">
      <div class="mb-3">
        <label for="abr_min_bitrate" class="form-label">{{ $t('config.abr_min_bitrate') }}</label>
        <input type="number" class="form-control" id="abr_min_bitrate" min="100" max="100000" placeholder="2000" v-model="config.abr_min_bitrate" />
        <div class="form-text">{{ $t('config.abr_min_bitrate_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_max_bitrate" class="form-label">{{ $t('config.abr_max_bitrate') }}</label>
        <input type="number" class="form-control" id="abr_max_bitrate" min="100" max="100000" placeholder="15000" v-model="config.abr_max_bitrate" />
        <div class="form-text">{{ $t('config.abr_max_bitrate_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_step_down_pct" class="form-label">{{ $t('config.abr_step_down_pct') }}</label>
        <input type="number" class="form-control" id="abr_step_down_pct" min="1" max="50" placeholder="15" v-model="config.abr_step_down_pct" />
        <div class="form-text">{{ $t('config.abr_step_down_pct_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_step_down_hard_pct" class="form-label">{{ $t('config.abr_step_down_hard_pct') }}</label>
        <input type="number" class="form-control" id="abr_step_down_hard_pct" min="1" max="80" placeholder="30" v-model="config.abr_step_down_hard_pct" />
        <div class="form-text">{{ $t('config.abr_step_down_hard_pct_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_step_up_pct" class="form-label">{{ $t('config.abr_step_up_pct') }}</label>
        <input type="number" class="form-control" id="abr_step_up_pct" min="1" max="50" placeholder="6" v-model="config.abr_step_up_pct" />
        <div class="form-text">{{ $t('config.abr_step_up_pct_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_cooldown_ms" class="form-label">{{ $t('config.abr_cooldown_ms') }}</label>
        <input type="number" class="form-control" id="abr_cooldown_ms" min="200" max="5000" placeholder="750" v-model="config.abr_cooldown_ms" />
        <div class="form-text">{{ $t('config.abr_cooldown_ms_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_good_windows" class="form-label">{{ $t('config.abr_good_windows') }}</label>
        <input type="number" class="form-control" id="abr_good_windows" min="1" max="20" placeholder="6" v-model="config.abr_good_windows" />
        <div class="form-text">{{ $t('config.abr_good_windows_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_loss_bad_pct" class="form-label">{{ $t('config.abr_loss_bad_pct') }}</label>
        <input type="number" class="form-control" id="abr_loss_bad_pct" min="0" max="100" placeholder="3" v-model="config.abr_loss_bad_pct" />
        <div class="form-text">{{ $t('config.abr_loss_bad_pct_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_loss_very_bad_pct" class="form-label">{{ $t('config.abr_loss_very_bad_pct') }}</label>
        <input type="number" class="form-control" id="abr_loss_very_bad_pct" min="0" max="100" placeholder="8" v-model="config.abr_loss_very_bad_pct" />
        <div class="form-text">{{ $t('config.abr_loss_very_bad_pct_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_rtt_threshold_ms" class="form-label">{{ $t('config.abr_rtt_threshold_ms') }}</label>
        <input type="number" class="form-control" id="abr_rtt_threshold_ms" min="1" max="10000" placeholder="120" v-model="config.abr_rtt_threshold_ms" />
        <div class="form-text">{{ $t('config.abr_rtt_threshold_ms_desc') }}</div>
      </div>

      <div class="mb-3">
        <label for="abr_jitter_threshold_ms" class="form-label">{{ $t('config.abr_jitter_threshold_ms') }}</label>
        <input type="number" class="form-control" id="abr_jitter_threshold_ms" min="0" max="10000" placeholder="25" v-model="config.abr_jitter_threshold_ms" />
        <div class="form-text">{{ $t('config.abr_jitter_threshold_ms_desc') }}</div>
      </div>
    </div>

  </div>
</template>

<style scoped>

</style>
