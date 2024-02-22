<template>
  <input
  :type="type_"
  :placeholder="placeholder_"
  class="inputGeneral"
  @blur="focused"
  @focus="unfocused"
  >
</template>
    
<script>
export default {
  name: 'InputParam',
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
        appConfig,
    }
  },
  computed: {
    switchDM() {
      const darkOrLight = this.isDark
      ? this.appConfig.colorsDark.backgroundColor_
      : this.appConfig.colorsLight.backgroundColor_

      const borderColor = this.appConfig.colorsLight.borderBoxColor

      const textColor = this.isDark
      ? this.appConfig.colorsDark.textPrimaryColor
      : this.appConfig.colorsLight.textPrimaryColor

      const style = {}

      style['background-color'] = darkOrLight
      style['color'] = textColor
      style['border-color'] = borderColor

      return style
    },
  },
  methods: {
    focused(e) {
      e.target.style.borderColor = "";
      e.target.style.boxShadow = "";
      e.target.style.color = "";
      e.target.style.setProperty('--placeholder-color', '')

    },
    unfocused(e) {
      const coloroxShadowFocused = this.isDark ? this.appConfig.colorsDark.primaryColor_: this.appConfig.colorsLight.primaryColor_

      e.target.style.borderColor = this.isDark ? this.appConfig.colorsDark.primaryColor_: this.appConfig.colorsLight.primaryColor_
      e.target.style.boxShadow = "inset 0 0 5px 1px " + coloroxShadowFocused

      e.target.style.setProperty('--placeholder-color', coloroxShadowFocused)
    }
  }
}
</script>

<style scoped>
input.inputGeneral {
  border-style: solid;
  border-width: 2px;
  height: 35px;
  width: 320px;
  box-shadow: inset 0 0 5px 0 #AAA;
  border-radius: 5px;
  text-align: center;
  margin: 8px 0;
}
input.inputGeneral::placeholder {
  color: var(--placeholder-color);
}
</style>