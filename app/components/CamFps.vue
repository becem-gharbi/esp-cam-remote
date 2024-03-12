<template>
  <n-tag type="success">
    {{ fps }} FPS
    <template #icon>
      <naive-icon name="ph:film-reel" />
    </template>
  </n-tag>
</template>

<script setup>
const fps = useFps('img-stream')
</script>
