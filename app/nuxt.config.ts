// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  devtools: {
    enabled: false
  },
  modules: [
    '@nuxtjs/tailwindcss',
    '@bg-dev/nuxt-naiveui'
  ],
  naiveui: {
    colorModePreference: 'light'
  }
})
