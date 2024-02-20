// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  app: {
    baseURL: ""
  },
  components: [
    { path: '~/components/atoms',
      pathPrefix: false
    },
    { path: '~/components/molecules',
      pathPrefix: false
    },
    { path: '~/components/organism',
      pathPrefix: false
    },
    '~/components',
  ],
  modules: [
    'nuxt-icon'
  ]
})