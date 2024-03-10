<template>
  <div />
</template>

<script setup lang="ts">
onMounted(() => {
  updateViewer(true)
  document.addEventListener('visibilitychange', () => {
    updateViewer(!document.hidden)
  })
})
</script>
