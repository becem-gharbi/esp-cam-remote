// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  ssr: false,
  devtools: {
    enabled: false
  },
  modules: [
    '@nuxtjs/tailwindcss',
    '@bg-dev/nuxt-naiveui',
    '@kgierke/nuxt-basic-auth'
  ],
  naiveui: {
    colorModePreference: 'light'
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
