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

      <form>
        <div
        class="entries"
        v-for="entry in entries"
        >

          <div>
            {{ entry.title }}
          </div>
          <div>
            
            <InputParam
            v-if="!entry.radio"
            :style="entry.button ? {'width': '240px'}:{}"
            v-model="entry.value_"
            :type_="entry.type_" :placeholder_="entry.placeholder"
            @change="(e:any) => {
              const input_ = e.target.value
              entry.value_ = input_
            }"
            />

            <v-radio-group
            v-model="entry.value_"
            inline
            v-if="entry.radio"
            :style="{
              display: 'flex',
              justifyContent: 'space-between',
              width: '100%'
            }"
            >
              <v-radio
              v-for="option in entry.options"
              :label="option"
              :value="option"
              ></v-radio>
            </v-radio-group>

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
      </form>

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

        <!--Solo para pruebas removible
        <AtomButton
        @click="testing"
        height="35px"
        width="150px"
        :style="{'margin-top':'50px', backgroundColor: 'red'}"
        >
          Test
        </AtomButton>
        -->
      </div>
    </AtomBox>

    <v-switch
      v-model="isNano"
      :label="isNano ? `x-coordinate in Nanometers`:`x-coordinate in Raman Shift`"
    ></v-switch>

    <Chart
    :intensity="intensity"
    :nanometers="nanometers"
    :rs="rs"
    />

    <AtomButton
    @click="csvDownloader"
    height="35px"
    width="150px"
    :style="{'margin-top':'50px', backgroundColor: 'red'}"
    >
      Download .csv
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

// the Global states to switch dark mode
const isDark = useIsDark().isDark
const isNano = useIsNano().isNano
const setIsNano = useIsNano().setIsNano
const appConfig = useAppConfig().theme
/////////////////////////////////////////

const intensity: any = ref<Array<number>>([])   //Set the state to intensity data
const nanometers: any = ref<Array<number>>([])  //Set the state to nanometer data
const rs: any = ref<Array<number>>([])  //Set the state to nanometer data

// The array below store the input parameters, for example:
// - IP of the MCU
// - Time constant
// - Min lambda
// - Max lambda
const entries = ref([
  {
    title: "Commmunication",
    value_: "",
    placeholder: 'Write the IP of the ESP32',
    button: false,
    type_: 'text',
    radio: false 
    
  },
  {
    title: "Time constant (ms)",
    value_: '',
    placeholder: 'Introduce the time constant',
    button: false,
    type_: 'number',
    radio: true,
    options: ['10', '100', '1000']
  },
  {
    title: "Minimum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the minimum wavelenght',
    button: false,
    type_: 'number',
    radio: false,
  },
  {
    title: "Maximum Wavelenght (nm)",
    value_: '',
    placeholder: 'Introduce the maximum wavelenght',
    button: false,
    type_: 'number',
    radio: false
  },
  {
    title: "Name of the file",
    value_: '',
    placeholder: 'Introduce the name of the .csv file',
    button: false,
    type_: 'text',
    radio: false
  },
])
var ws: any = null;  // Set the variable ws: websocket

// Function executed when "Download .csv" is clicked ////
function csvDownloader() {
  const csv = generateCsvContent();
  createCsvDownloadLink(csv);
}
/////////////////////////////////////////////////////////

// This function build the .csv file ////////////////////
function generateCsvContent() {
  let csv = 'Raman shift (1/cm), Intensity (a.u)\n';
  nanometers.value.map((e: any, i: any) => {
    csv += `${e},${intensity.value[i]}`;
    csv += '\n';
  })
  return csv;
}
////////////////////////////////////////////////////////////

// This function create the link t download ////////////////
function createCsvDownloadLink(csv: string) {
  const l = entries.value.length;
  const anchor = document.createElement('a');
  anchor.href = 'data:text/csv;charset=utf-8,' + encodeURIComponent(csv);
  anchor.target = '_blank';
  anchor.download = entries.value[l-1].value_;
  anchor.click();
}
////////////////////////////////////////////////////////////

// Logics to the switch to dark mode
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
/////////////////////////////////////////////////////////////

// Logics of the change to dark mode
const backgroundSecondaryColorSwitch = computed(() => {
  const style: any = {}
  const color = isDark ? appConfig.colorsDark.backgroundSecondaryColor_:appConfig.colorsLight.backgroundSecondaryColor_

  style['box-shadow'] = "0 0 10px 0 " + color

  return style 
})
///////////////////////////////////////

// Clean the area of the plot ////////////////////////
function cleanGraph() {
  intensity.value = []
  nanometers.value = []
  rs.value = []
}
//////////////////////////////////////////////////////

// Send a signal via WebSocket to stop the process ///
function stopSignal(){
    ws.send("stop");
}
//////////////////////////////////////////////////////

// Send a signal with the parameters to start ////////
function getReadings(){
    ws.send(JSON.stringify({
      'tau': entries.value[1].value_,
      'lambda1': 4*entries.value[2].value_,
      'lambda2': 4*entries.value[3].value_,
    }));
}
//////////////////////////////////////////////////////

// Open the WebSocket connection /////////////////////
function onOpen(event: any) {
    console.log('Connection opened');
    getReadings();
}
//////////////////////////////////////////////////////

// Open the webSocket connection to stop the process //
function onOpenStop(event: any) {
    console.log('Connection opened to close');
    stopSignal();
}
//////////////////////////////////////////////////////

// Close the webSocket connection ///////////////////
function onClose(event: any) {
    console.log('Connection disconnected');
    ws.close();
}
/////////////////////////////////////////////////////

// Function executed when button "start process" is clicked
function handleButtonStartProcess(){
  let gateway = `ws://${entries.value[0].value_}/ws`;  //Set the gateway to connect to the MCU
  ws = new WebSocket(gateway);                         //Instance the WS connection

  // Clean data
  if (intensity.value.length > 0 && nanometers.value.length > 0) {
    intensity.value = []
    nanometers.value = []
    rs.value = []
  }
  ws.onopen = onOpen;         // Open connection
  ws.onmessage = onMessage;   // Receive data from MCU
  ws.onclose = onClose;       // Close connection
}
/////////////////////////////////////////////////////////////

// Function executed when button "stop process" is clicked
function handleButtonStopProcess() {
  let gateway = `ws://${entries.value[0].value_}/ws`;
  ws = new WebSocket(gateway);
  ws.onopen = onOpenStop;
  ws.onmessage = onMessage;
  ws.onclose = onClose;
}
/////////////////////////////////////////////////////////////

// Handle the messages from MCU /////////////////////////////
function onMessage(event: any) {
    const obj = JSON.parse(event.data)
    const voltage = parseFloat(obj.voltaje)
    const nanometer = parseFloat(obj.nanometer)
    const rs_ = (1/532-1/nanometer)*(10**7)
    
    intensity.value = [...intensity.value, voltage]
    nanometers.value = [...nanometers.value, nanometer]
    rs.value = [...rs.value, rs_.toFixed(2)]
    //console.log(intensity.value)
    //console.log(nanometers.value)
}
/////////////////////////////////////////////////////////////
</script>

<!--Below it is the styles of the frontend-->
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