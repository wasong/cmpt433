import React, { Component } from 'react'
import Radium from 'radium'

import Paper from 'material-ui/Paper'

import Card from '../Card'
import Door from '../Door'
import Alarm from '../Alarm'
import Keypad from '../Keypad'

const styles = {
  wrapper: {
    display: 'flex',
    flexDirection: 'column',
    flex: 1,
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
  state = {}

  render() {
    const { onClick } = this.props
    return (
      <div style={styles.wrapper}>
        <Paper onClick={() => onClick('door')} style={styles.paper} zDepth={1}>
          <Card><Door /></Card>
        </Paper>
        <Paper onClick={() => onClick('alarm')} style={styles.paper} zDepth={1}>
          <Card statusType="success"><Alarm /></Card>
        </Paper>
        <Paper onClick={() => onClick('keypad')} style={styles.paper} zDepth={1}>
          <Card><Keypad /></Card>
        </Paper>
      </div>
    )
  }
}

export default Radium(Monitors)
