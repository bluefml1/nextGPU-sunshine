import{c as t,a,i as o}from"./_plugin-vue_export-helper-D7RxQbao.js";import{N as s}from"./Navbar-CToVr4mZ.js";import{M as c}from"./monitor-2uGI7hbE.js";/**
 * @license lucide-vue-next v0.577.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */const l=t("forward",[["path",{d:"m15 17 5-5-5-5",key:"nf172w"}],["path",{d:"M4 18v-2a4 4 0 0 1 4-4h12",key:"jmiej9"}]]);/**
 * @license lucide-vue-next v0.577.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */const u=t("hash",[["line",{x1:"4",x2:"20",y1:"9",y2:"9",key:"4lhtct"}],["line",{x1:"4",x2:"20",y1:"15",y2:"15",key:"vyu0kd"}],["line",{x1:"10",x2:"8",y1:"3",y2:"21",key:"1ggp8o"}],["line",{x1:"16",x2:"14",y1:"3",y2:"21",key:"weycgp"}]]);let p=a({components:{Navbar:s,Forward:l,Hash:u,Monitor:c},inject:["i18n"],methods:{registerDevice(y){let n=document.querySelector("#pin-input").value,i=document.querySelector("#name-input").value;document.querySelector("#status").innerHTML="";let r=JSON.stringify({pin:n,name:i});fetch("./api/pin",{method:"POST",headers:{"Content-Type":"application/json"},body:r}).then(e=>e.json()).then(e=>{e.status===!0?(document.querySelector("#status").innerHTML=`<div class="alert alert-success" role="alert">${this.i18n.t("pin.pair_success")}</div>`,document.querySelector("#pin-input").value="",document.querySelector("#name-input").value=""):document.querySelector("#status").innerHTML=`<div class="alert alert-danger" role="alert">${this.i18n.t("pin.pair_failure")}</div>`})}}});o(p);
