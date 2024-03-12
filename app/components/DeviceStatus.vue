<template>
  <n-tag v-if="$device.connected.value" type="success">
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
