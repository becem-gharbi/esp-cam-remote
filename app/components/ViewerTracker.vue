<template>
  <div />
</template>

<script setup lang="ts">
const { $mqtt, $device, $config } = useNuxtApp()

const visibility = ref(true)

onMounted(() => {
  document.addEventListener('visibilitychange', () => {
    visibility.value = document.visibilityState === 'visible'
  })
})

const viewer = computed(() => {
  return visibility.value && $device.connected.value
})

watch(viewer, (newValue, oldValue) => {
  if (newValue === false && oldValue === undefined) { return }
  updateViewer(newValue)
}, {
  immediate: true
})

function updateViewer (state: boolean) {
  /* eslint-disable no-console */
  console.log('ℹ️ 󠀠viewer status', state)
  const topic = `device/${$config.public.device.id}/command/custom`
  const message = JSON.stringify({ viewer: state })
  $mqtt.client.publish(topic, message, { qos: 2, retain: false })
}
</script>
