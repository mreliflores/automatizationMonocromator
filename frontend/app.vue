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
    :style="backgroundColorSwitch"
    >
      <div>
        Parameters
      </div>

      
      <div
      class="entries"
      v-for="entry in entries"
      >

        <div>
          {{ entry.title }}
        </div>
        <div>
          
          <InputParam
          :style="entry.button ? {'width': '240px'}:{}"
          v-model="entry.value_"
          type_="text" :placeholder_="entry.placeholder"
          @change="(e:any) => {
            const input_ = e.target.value
            entry.value_ = input_
            console.log('o')
          }"
          />
          <AtomButton
          :style="{'margin-left': '10px'}"
          height="35px"
          width="70px"
          v-if="entry.button"
          >
            Get IP
          </AtomButton>
        </div>
      </div>

      <AtomButton
      @click="handleValidateButtonClick"
      height="35px"
      width="150px"
      :style="{'margin-top':'50px'}"
      >
        Send Command
      </AtomButton>
      
      This is a preview of the changes in the form
      <pre>{{ JSON.stringify(entries, null, 2) }}
      </pre>
      
    </div>

    <Chart />
  </div>

  <footer>
    Footer
  </footer>
</template>

<script lang="ts" setup>
import '~/assets/css/main.css'

const isDark = useIsDark().isDark
const appConfig = useAppConfig().theme

const entries = ref([
  {
    title: "Commmunication",
    value_: "",
    placeholder: 'Write the IP of the ESP32',
    button: false
  },
  {
    title: "Time constant (ms)",
    value_: '',
    placeholder: 'Introduce the time constant',
    button: false
  },
  {
    title: "Minimum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the minimum wavelenght',
    button: false
  },
  {
    title: "Maximum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the minimum wavelenght',
    button: false
  },
])
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

function getIP(){
    ws.send("getIP");
}

function onOpen(event: any) {
    console.log('Connection opened');
    getReadings();
}

function handleValidateButtonClick() {
  let gateway = `ws://${entries.value[0].value_}/ws`;
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
  border-width: 3px;
  border-style: solid;
  border-radius: 10px;
  width: 80%;
  padding: 60px 15px;
  margin: 30px 15px;
}

.entries {
  display: flex;
  flex-direction: column;
}

@media (max-width: 800px) {
  .all {
    flex-direction: column;
  }
}
</style>