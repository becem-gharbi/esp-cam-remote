<template>
  <naive-config>
    <div class="page justify-center items-center">
      <cam-display />
      <viewer-tracker />
      <mqtt-status class="fixed bottom-4 right-4" />
    </div>
  </naive-config>
</template>

<style scoped>
.page {
  min-height: 100vh;
  min-height: 100dvh;
  width: 100%;
  display: flex;
  flex-direction: column;
}
</style>
