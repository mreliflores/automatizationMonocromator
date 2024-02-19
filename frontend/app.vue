<template>
  <header>
    Header
  </header>

  <div class="all">
    <div
    class="parameters"
    >
      Parameters
      <div>
        Comunication
        <input v-model="ip" type="text">
      </div>
      <form action="">
        <label for="time_constant">
          Time constant
          <input
          v-model="tau"
          type="number"
          id="time_constant"
          name="time_constant"
          >
        </label>
      </form>
      <button 
      class="buttonStart"
      @click="handleValidateButtonClick"
      >
        Send command
      </button>
    </div>

    <chart />
  </div>

  <footer>
    Footer
  </footer>
</template>

<script lang="ts" setup>
import chart from './components/chart.vue';

const ip = ref("");
const tau = ref("");
var ws: any;

function getReadings(){
    ws.send("getReadings");
}

function onOpen(event: any) {
    console.log('Connection opened');
    getReadings();
}

function handleValidateButtonClick() {
  let gateway = `ws://${ip.value}/ws`;
  ws = new WebSocket(gateway);
  ws.onopen = onOpen;
  ws.onmessage = onMessage;
}

function onMessage(event: any) {
    console.log(event.data);
    //var myObj = JSON.parse(event.data);
    //var keys = Object.keys(myObj);

    //for (var i = 0; i < keys.length; i++){
    //    var key = keys[i];
    //    document.getElementById(key).//innerHTML = myObj[key];
    //}
}

</script>

<style>
html, body, head {
  margin: 0;
  height: 100%;
  background-color: #222;
}

#__nuxt {
  height: 95%;
}

header {
  height: 50px;
}

footer {
  height: 150px;
}

.all {
  display: flex;
  justify-content: space-around;
  align-items: center;
  height: 100%;
  background-color: #1155cc;
}

.parameters {
  display: flex;
  flex-direction: column;
  align-items: center;
  background-color: #ccc;
  width: 40%;
}

button, input[type="submit"], input[type="reset"], input[type="text"], input[type="number"] {
	background: none;
	color: inherit;
	border: none;
	padding: 0;
	font: inherit;
	cursor: pointer;
	outline: inherit;
}

.buttonStart {
  border-radius: 5px;
  border: 1px solid #ccc;
  height: 35px;
  width: 150px;
  background-color: #1155cc;
  color: white;
}

@media (max-width: 800px) {
  .all {
    flex-direction: column;
  }
}
</style>