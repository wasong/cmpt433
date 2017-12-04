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

  handleOnClick = () => {
    console.log('click')
    socket.emit('setCode', 'setCode', this.state.value)
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
