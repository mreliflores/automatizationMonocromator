<template>
<button
:style="switchStyleDarkMode"
class="buttonStart"
>
  <slot />
</button>
</template>

<script lang="ts" setup>

var isDark = useIsDark().isDark
var appConfig = useAppConfig().theme
var props = defineProps({
  height: String,
  width: String
})

const switchStyleDarkMode = computed(() => {
  const style: any = {
  'width': props.width,
  'height': props.height,
  }


  const backC = isDark.value ? appConfig.colorsDark.primaryColor_:appConfig.colorsLight.primaryColor_

  style['background-color'] = backC

  return style
})

</script>

<style>
.buttonStart {
  border-radius: 5px;
  border: 1px solid #ccc;
  color: white;
}
</style>