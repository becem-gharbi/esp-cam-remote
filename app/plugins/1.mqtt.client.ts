import MQTT from 'mqtt'

export default defineNuxtPlugin(async (nuxtApp) => {
  const connected = useState('mqtt-connected', () => false)

  const mqttClient = await MQTT.connectAsync(nuxtApp.$config.public.mqtt.uri, {
    keepalive: 90,
    reconnectPeriod: 1000,
    username: nuxtApp.$config.public.mqtt.username,
    password: nuxtApp.$config.public.mqtt.password
  })

  connected.value = true

  mqttClient.on('disconnect', () => (connected.value = false))
  mqttClient.on('offline', () => (connected.value = false))
  mqttClient.on('end', () => (connected.value = false))
  mqttClient.on('close', () => (connected.value = false))
  mqttClient.on('connect', () => (connected.value = true))

  return {
    provide: {
      mqtt: {
        connected,
        client: mqttClient
      }
    }
  }
})
