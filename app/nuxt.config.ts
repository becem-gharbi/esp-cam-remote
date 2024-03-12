// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  ssr: false,
  spaLoadingTemplate: true,
  devtools: {
    enabled: false
  },
  modules: [
    '@nuxtjs/tailwindcss',
    '@bg-dev/nuxt-naiveui',
    '@kgierke/nuxt-basic-auth'
  ],
  naiveui: {
    colorModePreference: 'dark'
  },
  basicAuth: {
    enabled: true
  },
  runtimeConfig: {
    public: {
      device: {
        id: ''
      },
      mqtt: {
        uri: '',
        username: '',
        password: ''
      }
    }
  }
})
