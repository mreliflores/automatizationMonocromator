<template>
  <div class="placeButton">
    <button 
    class="buttonStart"
    @click="handleValidateButtonClick"
    >
      Get Data
    </button>
  </div>
</template>

<script lang="ts" setup>
var gateway = `ws://192.168.1.100/ws`;
var ws: any;

function getReadings(){
    ws.send("getReadings");
}

function onOpen(event: any) {
    console.log('Connection opened');
    getReadings();
}

function handleValidateButtonClick() {
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
}

#__nuxt {
  height: 100%;
}

.placeButton {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100%;
}

button, input[type="submit"], input[type="reset"] {
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
  width: 90px;
  background-color: #1155cc;
  color: white;
}
</style>