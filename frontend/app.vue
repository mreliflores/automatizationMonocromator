<template>
  <nav
  :style="{
    ...backgroundColorSwitch
  }"
  >
    Header
    <AtomToggleBox 
      height="25px"
      width="40px"
    />
</nav>

  <div 
  :style="backgroundColorSwitch"
  class="all">
    <AtomBox>
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
          :type_="entry.type_" :placeholder_="entry.placeholder"
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

      <div
      :style="{
        width: '100%',
        display: 'flex',
        justifyContent: 'space-evenly' 
      }"
      >
        <AtomButton
        @click="handleButtonStartProcess"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px'}"
        >
          Start process
        </AtomButton>
        <AtomButton
        @click="handleButtonStopProcess"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px', backgroundColor: 'red'}"
        >
          Stop process
        </AtomButton>
      </div>
    </AtomBox>

    <Chart />
  </div>

  <footer
  :style="backgroundColorSwitch"
  >
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
    button: false,
    type_: 'text'
  },
  {
    title: "Time constant (ms)",
    value_: '',
    placeholder: 'Introduce the time constant',
    button: false,
    type_: 'number'
  },
  {
    title: "Minimum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the minimum wavelenght',
    button: false,
    type_: 'number'
  },
  {
    title: "Maximum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the minimum wavelenght',
    button: false,
    type_: 'number'
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

const backgroundSecondaryColorSwitch = computed(() => {
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
    ws.send(JSON.stringify({
      'tau': entries.value[1].value_,
      'lambda1': entries.value[2].value_,
      'lambda2': entries.value[3].value_,
    }));
}

function onOpen(event: any) {
    console.log('Connection opened');
    getIP();
}

function onOpenStop(event: any) {
    console.log('Connection opened');
    getReadings();
}

function handleButtonStartProcess() {
  let gateway = `ws://${entries.value[0].value_}/ws`;
  ws = new WebSocket(gateway);
  ws.onopen = onOpen;
  ws.onmessage = onMessage;
}

function handleButtonStopProcess() {
  let gateway = `ws://${entries.value[0].value_}/ws`;
  ws = new WebSocket(gateway);
  ws.onopen = onOpenStop;
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
  height: 95%;
}

nav {
  display: flex;
  justify-content: space-between;
  align-items: center;
  right: 0;
  left: 0;
  padding: 0 15px;
  position: fixed;
  height: 50px;
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
  padding: 60px 0;
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