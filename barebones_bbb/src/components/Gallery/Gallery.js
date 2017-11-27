import React, { Component } from 'react'
import Radium from 'radium'

import Image from './Image'

const defaultUrl = 'https://localhost:8088/grabber0'

class Gallery extends Component {
  state = {
    position: 1,
    imageUrl: null,
    intervalId: null,
  }

  setImage = (position) => {
    this.setState({
      position,
      imageUrl: position < 10 ?
        `${defaultUrl}0${position}.jpeg` :
        `${defaultUrl}${position}.jpeg`,
    })
  }

  setPosition = () => {
    const { position } = this.state
    const newPosition = position < 19 ? position + 1 : 1

    this.setImage(newPosition)
  }

  showImages = () => {
    const intervalId = setInterval(this.setPosition, 500)
    this.setState({
      intervalId,
    })
  }


  stopImages = () => clearInterval(this.state.intervalId)

  render() {
    return (
      <div>
        <Image image={this.state.imageUrl} />
        <button onClick={this.showImages}>Show</button>
        <button onClick={this.stopImages}>Stop</button>
      </div>
    )
  }
}

export default Radium(Gallery)
