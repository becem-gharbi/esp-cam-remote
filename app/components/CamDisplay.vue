<template>
  <div>
    <img id="img-stream" alt="cam-stream">
  </div>
</template>

<script setup lang="ts">
const config = useRuntimeConfig()
const reader = new FileReader()

onMounted(() => {
  const imageStream = document.getElementById('img-stream')
  reader.onload = (event) => {
    if (event.target?.result) {
      imageStream?.setAttribute('src', event.target.result.toString())
    }
  }
})

useNuxtApp().$mqtt.client.on('message', onMessage)

function onMessage (topic: string, buffer: Buffer) {
  const isTopic = topic === `device/${config.public.device.id}/cam/stream`

  if (isTopic && reader.readyState !== reader.LOADING) {
    const blob = new Blob([buffer])
    reader.readAsDataURL(blob)
  }
}
</script>
