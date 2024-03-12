<template>
  <div>
    <img id="img-stream" alt="cam-stream" src="/favicon.ico">
  </div>
</template>

<script setup lang="ts">
const { $mqtt, $config } = useNuxtApp()
const reader = new FileReader()

onMounted(() => {
  const imageStream = document.getElementById('img-stream')

  reader.onload = (event) => {
    if (event.target?.result) {
      imageStream?.setAttribute('src', event.target.result.toString())
    }
  }
})

$mqtt.client.on('message', onMessage)
$mqtt.client.subscribe(`device/${$config.public.device.id}/cam/stream`)

function onMessage (topic: string, buffer: Buffer) {
  const isTopic = topic === `device/${$config.public.device.id}/cam/stream`

  if (isTopic && reader.readyState !== reader.LOADING) {
    const blob = new Blob([buffer])
    reader.readAsDataURL(blob)
  }
}
</script>
