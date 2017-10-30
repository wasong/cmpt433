import "babel-polyfill"
import express from 'express'
import http from 'http'
import path from 'path'

const PORT = 3000
const app = express()

app.use(express.static(path.resolve(__dirname, '..', 'client', 'public')))

app.use('/', (req, res) => {
  res.sendFile('/index.html')
})


app.server = http.createServer(app)
app.server.listen(PORT, (req, res) => {
  console.log(`Listening on PORT ${PORT}`)
})
