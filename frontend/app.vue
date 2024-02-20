<template>
  <header
  :style="backgroundColorSwitch"
  >
    Header
    <AtomToggleBox 
      height="25px"
      width="40px"
    />
  </header>

  <div 
  :style="backgroundColorSwitch"
  class="all">
    <div
    class="parameters"
    >
      <div>
        Parameters
      </div>

      <div
      class="entries">
        <div>
          Communication
        </div>
        <InputParam
        :state="ip"
        type_="text" placeholder_="Hola"/>
      </div>

      <button 
      class="buttonStart"
      @click="handleValidateButtonClick"
      >
        Send command
      </button>
    </div>

    <Chart />
  </div>

  <footer>
    Footer
  </footer>
</template>

<script lang="ts" setup>


const isDark = useIsDark().isDark
const appConfig = useAppConfig().theme

const ip = ref("");
const tau = ref("");
var ws: any;

const backgroundColorSwitch = computed(() => {
  const style: any = {}
  if (isDark.value) {
    style['background-color'] = appConfig.colorsDark.backgroundColor_
    style['color'] = appConfig.colorsDark.textPrimaryColor
  } else {
    style['background-color'] = appConfig.colorsLight.backgroundColor_
    style['color'] = appConfig.colorsLight.textPrimaryColor
  }

  return style 
})

function getReadings(){
    ws.send("getReadings");
}

function onOpen(event: any) {
    console.log('Connection opened');
    getReadings();
}

function handleValidateButtonClick() {
  let gateway = `ws://${ip.value}/ws`;
  console.log(gateway)
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

/*
button, input[type="submit"], input[type="reset"], input[type="text"], input[type="number"] {
	background: none;
	color: inherit;
	border: none;
	padding: 0;
	font: inherit;
	cursor: pointer;
	outline: inherit;
}
*/

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
  background-color: #fff;
}

footer {
  height: 150px;
  background-color: aquamarine;
}

.all {
  display: flex;
  flex-direction: column;
  align-items: center;
  background-color: #222;
}

.parameters {
  display: flex;
  flex-direction: column;
  align-items: center;
  background-color: #ccc;
  width: 80%;
  padding: 60px 15px;
  margin: 30px 15px;
}

.entries {
  margin: 10px 0;
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