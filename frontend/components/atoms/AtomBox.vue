<template>
  <div
  class="atomBox"
  :style="isDark ? {
    borderColor: appConfig.colorsDark.primaryColor_,
    boxShadow: '0 0 30px 0 ' + appConfig.colorsDark.primaryColor_
  }:{
    borderColor: appConfig.colorsLight.primaryColor_,
    boxShadow: '0 0 30px 0 ' + appConfig.colorsLight.primaryColor_
  }"
  >
   <slot /> 
  </div>
</template>

<script lang="ts" setup>
const isDark = useIsDark().isDark
const appConfig = useAppConfig().theme


</script>

<style>
div.atomBox {
  display: flex;
  flex-direction: column;
  align-items: center;
  border-width: 3px;
  border-style: solid;
  border-radius: 10px;
  width: 80%;
  padding: 60px 15px;
  margin: 30px 15px;
}
</style>