<template>
  <n-tag v-if="connected" type="success">
    Device
    <template #icon>
      <naive-icon name="ph:check-circle" />
    </template>
  </n-tag>
  <n-tag v-else type="error">
    Device
    <template #icon>
      <naive-icon name="ph:x-circle" />
    </template>
  </n-tag>
</template>

<script setup lang="ts">
const config = useRuntimeConfig()
const connected = ref(false)

useNuxtApp().$mqtt.client.on('message', onMessage)

function onMessage (topic: string, buffer: Buffer) {
  const isTopic = topic === `device/${config.public.device.id}/report/status`

  if (isTopic) {
    connected.value = buffer.toString() === '{"status":"connected"}'
    updateViewer(connected.value)
  }
}
</script>
