<template>
  <div class="border p-4 bg-zinc-100">
    <p>{{ data }}</p>
  </div>
</template>

<script setup lang="ts">
const { $mqtt } = useNuxtApp()
const data = ref('no data')

$mqtt.client.on('message', onMessage)

function onMessage (topic: string, payload: Buffer) {
  if (topic) {
    data.value = payload.toString()
  }
}
</script>
