import io from 'socket.io-client'

const socket = io('http://192.168.7.2:4000')
socket.on('hello', (data) => {
  console.log(data)
})
