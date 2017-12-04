import React, { Component } from 'react'
import Radium from 'radium'

import TextField from 'material-ui/TextField'
import RoundedButton from 'components/Button/RoundedButton'
import socket from 'utils/socket'

class Keypad extends Component {
  state = {
    value: '',
  }

  handleOnChange = (e) => {
    this.setState({
      value: e.target.value,
    })
  }

  handleSetCodeRes = (res) => {
    console.log(res)
    socket.removeListener('setCodeResponse', this.handleSetCodeRes)
  }

  handleOnClick = () => {
    socket.emit('setCode', 'setCode', this.state.value)
    socket.on('setCodeResponse', this.handleSetCodeRes)
  }

  render() {
    return (
      <div>
        <TextField hintText="Enter new passcode" value={this.state.value} onChange={this.handleOnChange} />
        <RoundedButton onClick={this.handleOnClick} label="Change" />
      </div>
    )
  }
}

export default Radium(Keypad)
