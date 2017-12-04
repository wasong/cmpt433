import React, { Component } from 'react'
import Radium from 'radium'

import TextField from 'material-ui/TextField'
import RoundedButton from 'components/Button/RoundedButton'
import socket from 'utils/socket'

const styles = {
  root: {
    display: 'flex',
    justifyContent: 'center',
    alignItems: 'center',
    flexDirection: 'column',
    marginTop: 20,
  },
  key: {
    textAlign: 'center',
    fontSize: 30,
    fontWeight: 'bold',
    margin: '30px 0 50px',
  },
}

class Audio extends Component {
  state = {
    audioIntervalID: null,
    audio: null,
    value: '',
  }

  componentDidMount = () => {
    if (!this.state.audioIntervalID) {
      const audioIntervalID = setInterval(() => {
        socket.emit('getSound', 'getSound')
      }, 2500)

      this.setState({
        audioIntervalID,
      })

      socket.on('getSoundResponse', this.handleGetSoundRes)
    }
  }

  componentWillUnmount = () => {
    clearInterval(this.state.audioIntervalID)
    socket.removeListener('getSoundResponse', this.handleGetSoundRes)
  }

  handleGetSoundRes = (res) => {
    this.setState({
      audio: res,
    })
  }

  handleSetSoundRes = (res) => {
    console.log(res)
    socket.removeListener('setSoundResponse', this.handleSetSoundRes)
  }

  handleOnClick = (alarm) => {
    socket.emit('setSound', 'setSound', alarm)
    socket.on('setSoundResponse', this.handleSetSoundRes)
  }

  render() {
    return (
      <div style={styles.root}>
        <div style={styles.key}>{this.state.audio}</div>
        <div>
          <div>Select Alarm</div>
          <RoundedButton onClick={() => this.handleOnClick(0)} label="First" />
          <RoundedButton onClick={() => this.handleOnClick(1)} label="Second" />
        </div>
      </div>
    )
  }
}

export default Radium(Audio)
