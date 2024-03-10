import type { MqttClient } from 'mqtt'

export default defineNuxtPlugin((nuxtApp) => {
  const config = useRuntimeConfig()
  const connected = useState('mqtt-connected', () => false)

  let mqttClient: MqttClient | undefined

  async function connect () {
    const { default: MQTT } = await import('mqtt')

    await mqttClient?.endAsync()

    mqttClient = await MQTT.connectAsync(config.public.mqtt.uri, {
      keepalive: 90,
      reconnectPeriod: 1000,
      username: config.public.mqtt.username,
      password: config.public.mqtt.password
    })

    connected.value = true

    mqttClient.on('disconnect', () => (connected.value = false))

    mqttClient.on('offline', () => (connected.value = false))

    mqttClient.on('end', () => (connected.value = false))

    mqttClient.on('close', () => (connected.value = false))

    mqttClient.on('connect', () => (connected.value = true))
  }

  nuxtApp.hook('app:mounted', connect)

  return {
    provide: {
      mqtt: {
        connect,
        connected,
        client: mqttClient
      }
    }
  }
})
