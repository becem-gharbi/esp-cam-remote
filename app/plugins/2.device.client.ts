export default defineNuxtPlugin(() => {
  const connected = useState('device-connected', () => false)
  const nuxtApp = useNuxtApp()

  nuxtApp.$mqtt.client.on('message', onMessage)

  nuxtApp.$mqtt.client.subscribe(`device/${nuxtApp.$config.public.device.id}/report/status`)

  function onMessage (topic: string, buffer: Buffer) {
    const isTopic = topic === `device/${nuxtApp.$config.public.device.id}/report/status`

    if (isTopic) {
      connected.value = buffer.toString() === '{"status":"connected"}'
    }
  }

  return {
    provide: {
      device: {
        connected
      }
    }
  }
})
