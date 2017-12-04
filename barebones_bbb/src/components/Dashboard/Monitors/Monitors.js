import React, { Component } from 'react'
import Radium from 'radium'

import Paper from 'material-ui/Paper'
import socket from 'utils/socket'

import Card from '../Card'
import Door from '../Door'
import Alarm from '../Alarm'

const styles = {
  wrapper: {
    display: 'flex',
    flexDirection: 'column',
    flex: 1,
    height: '100%',
    margin: -5,
  },
  paper: {
    height: 50,
    flex: 1,
    margin: 5,
    position: 'relative',
    cursor: 'pointer',
  },
}

class Monitors extends Component {
  state = {
    alarm: 'success',
    alarmIntervalID: null,
  }

  componentDidMount = () => {
    if (!this.state.alarmIntervalID) {
      const alarmIntervalID = setInterval(() => {
        socket.emit('getAlarm', 'getAlarm')
      }, 1000)

      this.setState({
        alarmIntervalID,
      })

      socket.on('getAlarmResponse', this.handleGetAlarm)
    }
  }

  componentWillUnmount = () => {
    clearInterval(this.state.alarmIntervalID)
    socket.removeListener('getAlarmResponse', this.handleGetAlarm)
  }

  handleGetAlarm = (res) => {
    const door = res.slice(0, 1)
    const audio = res.slice(1, 2)
    const key = res.slice(2, 3)
    this.setState({
      door: parseInt(door, 10) ? 'error' : 'success',
      audio: parseInt(audio, 10) ? 'error' : 'success',
      key: parseInt(key, 10) ? 'error' : 'success',
    })
  }

  render() {
    const { onClick } = this.props
    return (
      <div style={styles.wrapper}>
        <Paper onClick={() => onClick('door')} style={styles.paper} zDepth={1}>
          <Card statusType={this.state.door}><Door /></Card>
        </Paper>
        <Paper onClick={() => onClick('alarm')} style={styles.paper} zDepth={1}>
          <Card statusType={this.state.audio}><Alarm /></Card>
        </Paper>
        <Paper onClick={() => onClick('keypad')} style={styles.paper} zDepth={1}>
          <Card statusType={this.state.key}>Keypad</Card>
        </Paper>
      </div>
    )
  }
}

export default Radium(Monitors)
