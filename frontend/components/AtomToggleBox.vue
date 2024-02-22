<template>
    <button 
        class="toggleDM"
        :style="styli"
        @click="setIsDark()"

    >
        <div 
            :style="switchDarkMode"
            class="toggleOn"
        >
            <MaterialSymbolsClearDayRounded
                :color="isDark
                ? appConfig.colorsDark.textPrimaryColor
                : appConfig.colorsLight.textPrimaryColor
                "
                size="15px"
                v-if="!isDark"
            />
            <MaterialSymbolsDarkMode
                :color="isDark
                ? appConfig.colorsDark.textPrimaryColor
                : appConfig.colorsLight.textPrimaryColor
                "
                size="15px"
                v-else
            />
        </div>
    </button>
</template>

<script>
import '~/assets/css/toggleDarkMode.css'

export default {
  name: 'AtomToggleBox',
  props: [
    'height',
    'width',
  ],
  data() {
    const style = {
      'height': this.height,
      'width': this.width,
      'border': '1px solid '+ this.appConfig.colorsLight.borderBoxColor,
      'box-shadow': "inset 0 0 5px 1px " + this.appConfig.colorsDark.primaryColor_
    }
    return {
      style
    }
  },
  setup() {
    const {isDark, setIsDark} = useIsDark()
    const appConfig = useAppConfig().theme
    return {
      isDark,
      setIsDark,
      appConfig
    }
  },
  computed: {
    switchDarkMode() {
      if(this.isDark) {
        const x = {
          'transform': 'translateX(65%)',
          'background-color': this.appConfig.colorsDark.backgroundColor_,
          'border': '1px solid ' + this.appConfig.colorsDark.borderBoxColor
        }
        return x
      } else {
        const x = {
          'transform': 'translateX(0%)',
          'background-color': this.appConfig.colorsLight.backgroundColor_,
          'border': '1px solid ' + this.appConfig.colorsLight.borderBoxColor
        }
        return x
      }
    },
    styli() {
      if(this.isDark) {
        this.style['box-shadow'] = "inset 0 0 5px 1px " + this.appConfig.colorsDark.primaryColor_
        return this.style
      } else {
        this.style['box-shadow'] = "inset 0 0 5px 1px " + this.appConfig.colorsLight.primaryColor_
        return this.style
      }
    }
  }
}
</script>