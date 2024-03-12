<template>
  <naive-config>
    <div class="page justify-center items-center p-1">
      <cam-display class="rounded-md overflow-hidden border dark:border-zinc-600" />

      <viewer-tracker />

      <section class="fixed bottom-4 flex gap-3 text-center">
        <cam-fps />
        <device-status />
        <mqtt-status />
      </section>
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
