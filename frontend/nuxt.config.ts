// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  app: {
    baseURL: ""
  },
  components: [
    { path: '~/components/atoms',
      pathPrefix: false
    },
    //{ path: '~/components/molecules',
      //pathPrefix: false
    //},
    //{ path: '~/components/organism',
      //pathPrefix: false
    //},
    '~/components',
  ],
  modules: ['@nuxtjs/google-fonts'],
  googleFonts: {
    families: {
      Lato: [700],
      Exo: [300],
      Caveat: true
    }
  }
})