<template>
  <nav
  :style="{
    ...backgroundSecondaryColorSwitch,
    ...backgroundColorSwitch
  }"
  >
    <div
    :style="{
      fontFamily: 'Caveat'
    }"
    >
      LabLaserUCV
    </div>
    <div
    :style="{
      display: 'flex',
      alignItems: 'center'
    }"
    >
      <div>Otras</div>
      <div>Opciones</div>
      <AtomToggleBox 
        height="25px"
        width="40px"
      />
    </div>
</nav>

  <div 
  :style="backgroundColorSwitch"
  class="all">
    <AtomBox>
      <div
      :style="{
        marginBottom: '25px'
      }"
      >
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
        justifyContent: 'space-evenly',
        flexWrap: 'wrap'
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
        @click="cleanGraph"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px'}"
        >
          Clean Graph
        </AtomButton>
        <AtomButton
        @click="handleButtonStopProcess"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px', backgroundColor: 'red'}"
        >
          Stop process
        </AtomButton>
        <!--Solo para pruebas removible-->
        
        <AtomButton
        @click="testing"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px', backgroundColor: 'red'}"
        >
          Test
        </AtomButton>
        
        <!--Solo para pruebas (removible)-->
      </div>
    </AtomBox>

    <Chart
    :intensity="intensity"
    :nanometers="nanometers"
    />
    <AtomButton
    @click="csvDownloader"
    height="35px"
    width="150px"
    :style="{'margin-top':'50px', backgroundColor: 'red'}"
    >
      Test_
    </AtomButton>
  </div>


  <footer
  :style="{
  ...backgroundColorSwitch,
  ...backgroundSecondaryColorSwitch
  }"
  >
    Footer
  </footer>
</template>

<script lang="ts" setup>
import '~/assets/css/main.css'
//import '@material/web/radio/radio.js';

const isDark = useIsDark().isDark
const appConfig = useAppConfig().theme

const intensity: any = ref<Array<number>>([])
const nanometers: any = ref<Array<number>>([])

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
    placeholder: 'Introduce the maximum wavelenght',
    button: false,
    type_: 'number'
  },
])
var ws: any = null;

function csvDownloader() {
  const csv = generateCsvContent();
  createCsvDownloadLink(csv);
}

function generateCsvContent() {
  let csv = 'Nanometers (nm), Intensity (a.u)\n';
  nanometers.value.map((e: any, i: any) => {
    csv += `${e},${intensity.value[i]}`;
    csv += '\n';
  })
  return csv;
}

function createCsvDownloadLink(csv: string) {
  const anchor = document.createElement('a');
  anchor.href = 'data:text/csv;charset=utf-8,' + encodeURIComponent(csv);
  anchor.target = '_blank';
  anchor.download = 'nameYourFileHere.csv';
  anchor.click();
}

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
  const color = isDark ? appConfig.colorsDark.backgroundSecondaryColor_:appConfig.colorsLight.backgroundSecondaryColor_

  style['box-shadow'] = "0 0 10px 0 " + color

  return style 
})

//Removible
function testing() {
  let i = 0
  let x: Array<number> = []
  let y: Array<number> = []
  setInterval(() => {
    if(i<5) {
      for(let j=i*50; j<(i+1)*50; j++) {
        
        x.push(j)
        y.push(2)
      }
      intensity.value = [...intensity.value, ...y]
      nanometers.value = [...nanometers.value, ...x]
      console.log(nanometers.value)
      x = []
      y= []
      i++
    }
  },1000)
}
//Removible

function cleanGraph() {
  intensity.value = []
  nanometers.value = []
}

function getReadings(){
    ws.send("getReadings");
}

function getIP(){
    ws.send(JSON.stringify({
      'tau': entries.value[1].value_,
      'lambda1': 4*entries.value[2].value_,
      'lambda2': 4*entries.value[3].value_,
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

function onClose(event: any) {
    console.log('Connection disconnected');
    ws.close();
}

function handleButtonStartProcess(){
  let gateway = `ws://${entries.value[0].value_}/ws`;
  ws = new WebSocket(gateway);
  if (intensity.value.length > 0 && nanometers.value.length > 0) {
    intensity.value = []
    nanometers.value = []
  }
  ws.onopen = onOpen;
  ws.onmessage = onMessage;
  ws.onclose = onClose;
}

function handleButtonStopProcess() {
  let gateway = `ws://${entries.value[0].value_}/ws`;
  ws = new WebSocket(gateway);
  ws.onopen = onOpenStop;
  ws.onmessage = onMessage;
  ws.onclose = onClose;
}

function onMessage(event: any) {
    const obj = JSON.parse(event.data)
    const voltage = parseFloat(obj.voltaje)
    const nanometer = parseFloat(obj.nanometer)
    intensity.value = [...intensity.value, voltage]
    nanometers.value = [...nanometers.value, nanometer]
    console.log(intensity.value)
    console.log(nanometers.value)
    //realTimeChart.data.datasets.forEach((dataset: any) => {
        //dataset.data.push(obj.voltaje);
    //});
    //realTimeChart.update()
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
  font-family: 'Exo', 'Nunito', sans-serif;
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