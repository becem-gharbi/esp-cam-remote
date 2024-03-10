<template>
  <div />
</template>

<script setup lang="ts">

onMounted(() => {
  onViewerChange(true)
  document.addEventListener('visibilitychange', () => {
    onViewerChange(!document.hidden)
  })
})

function onViewerChange (state: boolean) {
  const { $mqtt } = useNuxtApp()
  const config = useRuntimeConfig()
  const topic = `device/${config.public.device.id}/command/custom`
  $mqtt.client.publish(topic, JSON.stringify({ viewer: state }), { qos: 2, retain: false })
}
</script>
