import Express from 'express'
import bodyParser from 'body-parser'
import morgan from 'morgan'
import path from 'path'

const app = Express()
const PORT = process.env.PORT || 3000

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(morgan('combined'))

// expose static files
app.use(Express.static(path.resolve(__dirname, '..', 'public')))

app.get('*', (req, res) => {
  res.sendFile(path.resolve(__dirname, '..', 'public', 'index.html'))
})

app.listen(PORT, () => {
  console.log(`Listening on PORT: ${PORT}`)
})
