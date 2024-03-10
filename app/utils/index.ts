export function updateViewer (state: boolean) {
  const { $mqtt } = useNuxtApp()
  const config = useRuntimeConfig()
  const topic = `device/${config.public.device.id}/command/custom`
  $mqtt.client.publish(topic, JSON.stringify({ viewer: state }), { qos: 2, retain: false })
}
