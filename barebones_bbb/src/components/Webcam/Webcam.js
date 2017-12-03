import React, { Component } from 'react'
import Radium from 'radium'

import Slider from 'material-ui/Slider'
import RoundedButton from 'components/Button/RoundedButton'
import Image from './Image'

const defaultUrl = 'https://localhost:8088/grabber0'
const maxImages = 59
const intervalTime = 150

const styles = {
  root: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  slider: {
    width: '100%',
  },
}

class Gallery extends Component {
  state = {
    position: 1,
    imageUrl: null,
    intervalId: null,
    showing: false,
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
    const newPosition = position < maxImages ? position + 1 : 1

    this.setImage(newPosition)
  }

  showImages = () => {
    if (!this.state.showing) {
      const intervalId = setInterval(this.setPosition, intervalTime)
      this.setState({
        intervalId,
        showing: true,
      })
    }
  }

  stopImages = () => {
    clearInterval(this.state.intervalId)
    this.setState({
      intervalId: null,
      showing: false,
    })
  }

  render() {
    return (
      <div style={styles.root}>
        <Image image={this.state.imageUrl} />
        <Slider
          min={1}
          max={maxImages}
          step={1}
          value={this.state.position}
          onChange={(e, pos) => this.setImage(pos)}
          style={styles.slider}
        />
        <div>
          <RoundedButton onClick={this.showImages} primary label="Show" />
          <RoundedButton onClick={this.stopImages} primary label="Stop" />
        </div>
      </div>
    )
  }
}

export default Radium(Gallery)
