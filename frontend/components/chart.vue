<template>
  <div class="aquiChart">
    <canvas id="ploti">
    </canvas>
  </div>
</template>


<script>
import Chart from 'chart.js/auto';

export default {
  name: 'chart',
  data () {
    return {
      p: [
        { year: 2010, count: 10 },
        { year: 2011, count: 20 },
        { year: 2012, count: 15 },
        { year: 2013, count: 25 },
        { year: 2014, count: 22 },
        { year: 2015, count: 30 },
        { year: 2016, count: 28 },
      ]
    }
  },
  mounted () {
    const ctx = document.getElementById('ploti');
    new Chart(
      ctx,
      {
        type: 'bar',
        data: {
          labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
          datasets: [
            {
              label: "Caracas",
              data: [12, 19, 3, 5, 2, 3]
            },
            {
              label: "Caracas",
              data: [1, 15, 12, 7, 4, 9]
            }
          ]
        },
        options: {
          responsive: true
        }
      }
    );
  }
};

</script>

<style>
.aquiChart {
  display: flex;
  justify-content:center;
  align-items:center;
  height: 100%;
  width: 100%;
}

#ploti {
  width:100%;
}
</style>