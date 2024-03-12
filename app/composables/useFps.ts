export function useFps (id: string) {
  let interval: NodeJS.Timeout
  const every = 4000
  const fps = ref(0)
  let counter = 0

  onMounted(() => {
    const el = document.getElementById(id)
    if (el) {
      el.onload = () => counter++
      interval = setInterval(callback, every)
    }
  })

  onUnmounted(() => interval && clearInterval(interval))

  function callback () {
    fps.value = counter && Math.round(every / (1000 * counter))
    counter = 0
  }

  return fps
}
