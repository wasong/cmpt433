import Express from 'express'
import bodyParser from 'body-parser'
import morgan from 'morgan'
import path from 'path'
import http from 'http'

// import { socketListener } from './lib/socket'

const app = Express()
const PORT = process.env.PORT || 4000

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(morgan('combined'))

// expose static files
// dirname = '/public/dist'
app.use(Express.static(path.resolve(__dirname, '..')))
app.use(Express.static(path.resolve(__dirname, '..', 'index.html')))

app.get('*', (req, res) => {
  res.sendFile(path.resolve(__dirname, '..', 'index.html'))
})

// separate http server but also maintain express routes and middleware
app.server = http.createServer(app)

// start socket listener
// socketListener(app.server)

app.server.listen(PORT, () => {
  console.log(`Listening on PORT: ${PORT}`)
})
