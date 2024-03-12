<template>
  <n-tag v-if="$mqtt.connected.value" type="success">
    Mqtt
    <template #icon>
      <naive-icon name="ph:check-circle" />
    </template>
  </n-tag>
  <n-tag v-else type="error">
    Mqtt
    <template #icon>
      <naive-icon name="ph:x-circle" />
    </template>
  </n-tag>
</template>
