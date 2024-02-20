<template>
  <input
  :type="type_"
  :value="state"
  @input="$emit('update:modelValue', $event.target.value)"
  :placeholder="placeholder_"
  class="inputGeneral"
  :style="switchDM">
</template>
    
<script>
  export default {
    name: 'InputParam',
    data () {
      return {
        dati: ""
      }
    },
    props: {
      type_: {
        type: String
      },
      placeholder_: {
        type: String
      },
      state: {
        type: String
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
    computed: {
      switchDM() {
        const darkOrLight = this.isDark
        ? this.appConfig.colorsDark.backgroundColor_
        : this.appConfig.colorsLight.backgroundColor_

        const borderColor = this.isDark
        ? this.appConfig.colorsDark.primaryColor_
        : this.appConfig.colorsLight.primaryColor_

        const textColor = this.isDark
        ? this.appConfig.colorsDark.textPrimaryColor
        : this.appConfig.colorsLight.textPrimaryColor

        const style = {}

        style['background-color'] = darkOrLight

        style['color'] = textColor

        style['border-color'] = borderColor

        return style
      }
    }
  }
</script>

<style>
input.inputGeneral {
  border-style: solid;
  height: 30px;
  width: 280px;
  box-shadow: inset 0 0 5px 1px black;
  border-radius: 5px;
  border-width: 1px;
  text-align: center;
  margin: 3px 0;
}

input.inputGeneral:focus {
  box-shadow: inset 1px 1px 10px 1px #199930;
}
</style>