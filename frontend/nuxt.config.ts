// https://nuxt.com/docs/api/configuration/nuxt-config
import vuetify, { transformAssetUrls } from 'vite-plugin-vuetify'
export default defineNuxtConfig({
  app: {
    baseURL: ""
  },
  build: {
    transpile: ['vuetify'],
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
  modules: [
    '@nuxtjs/google-fonts',
    (_options, nuxt) => {
      nuxt.hooks.hook('vite:extendConfig', (config) => {
        // @ts-expect-error
        config.plugins.push(vuetify({ autoImport: true }))
      })
    },
  ],
  googleFonts: {
    families: {
      Lato: [700],
      Exo: [300],
      Caveat: true
    }
  },
  vite: {
    vue: {
      template: {
        transformAssetUrls,
      },
    },
  },
})