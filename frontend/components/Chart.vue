<template>
  <div class="aquiChart"
  :style="{
    display: 'flex',
    flexDirection: 'column'
  }"
  >
    <Line 
    :data="chartData" :options="chartOptions"
    updateMode="none">
    </Line>
    <AtomButton
    height="35px"
    width="150px"
    :style="{'margin-top':'50px', backgroundColor: 'red'}"
    >
      Test_
    </AtomButton>
    <div>{{ intensity[intensity.length-1] }}</div>
  </div>
</template>


<script >
import { Line } from 'vue-chartjs'
import { Chart as ChartJS, Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale, PointElement, LineElement, Colors } from 'chart.js'
ChartJS.register(Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale, PointElement, LineElement, Colors)


export default {
  name: 'Chart',
  components: {Line},
  props: {
    intensity: {
      type: Array,
      default: []
    },
    nanometers: {
      type: Array,
      default: []
    }
  },
  setup() {
    const isDark = useIsDark().isDark
    const appConfig = useAppConfig().theme
    return {
      isDark,
      appConfig
    }
  },
  data() {
    var realTimeChart;
    return {
      realTimeChart,
      chartData_: {
        labels: this.nanometers,//getDataNanometers,
        datasets: [
          {
            label: "Caracs",
            data: this.intensity,
            borderColor: '#36A2EB',
            backgroundColor: '#9BD0F5',
          },
          {
            label: "Caracs",
            data: this.intensity,
            borderColor: '#36A2EB',
            backgroundColor: '#9BD0F5',
          },
        ]
      },
      chartOptions_: {
        responsive: true,
        layout: {
          padding: {
            top: 20
          }
        },
      }
    }
  },
  computed: {
    chartData() {
      const backgroundColor = this.isDark ? this.appConfig.colorsDark.primaryAccentColor_:this.appConfig.colorsLight.primaryAccentColor_

      const borderColor = this.isDark ? this.appConfig.colorsDark.primaryColor_:this.appConfig.colorsLight.primaryColor_

      const data = {
        labels: this.nanometers,//getDataNanometers,
        datasets: [
          {
            label: "Signal",
            data: this.intensity,
            borderColor: borderColor,
            backgroundColor: backgroundColor,
            pointRadius: 0
          },
        ]
      }
      return data
    },
    chartOptions() {
      const color = this.isDark ? this.appConfig.colorsDark.textSecondaryColor:this.appConfig.colorsLight.textSecondaryColor

      const options = {
        animations: false,
        responsive: true,
        layout: {
          padding: {
            top: 20
          }
        },
        plugins: {
          title: {
            display: true,
            text: "Raman's Spectrum"
          }
        },
        scales: {
          x: {
            beginAtZero: true,
            title: {
              display: true,
              text: 'Nanometers (nm)',
              color: color
            },
            border: {
              display: true,
              color: color
            },
            grid: {
              display: false,
              color: color
            }
          },
          y: {
            title: {
              display: true,
              text: 'Intensity',
              color: color
            },
            border: {
              display: true,
              color: color
            },
            grid: {
              display: false,
              color: color
            }
          },
        }
      }
      return options
    }
  }
};

</script>

<style>
.aquiChart {
  display: flex;
  justify-content:center;
  align-items:center;
  margin: 60px 0;
  width: 80%;
}

</style>