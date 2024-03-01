<template>
  <div class="aquiChart">
    <canvas id="ploti">
    </canvas>
  </div>
</template>


<script >
import Chart from 'chart.js/auto';


export default {
  name: 'Chart',
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
  mounted () {
    const ctx = document.getElementById('ploti');
    const realTimeChart = new Chart(
      ctx,
      {
        type: 'line',
        data: {
          labels: this.nanometers,//getDataNanometers,
          datasets: [
            {
              label: "Caracas",
              data: this.intensity,//getDataIntensity  
            },
          ]
        },
        options: {
          responsive: true,
          layout: {
            padding: 20
          }
        }
      }
    );
  },
  computed: {
    getDataX() {
      return this.nanometers
    },
    getDataY() {
      return this.intensity
    },
  }
};

</script>

<style>
.aquiChart {
  display: flex;
  justify-content:center;
  align-items:center;
  margin: 60px 0;
  width: 100%;
}

#ploti {
  width:100%;
}
</style>