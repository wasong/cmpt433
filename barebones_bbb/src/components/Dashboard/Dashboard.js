import React, { Component } from 'react'
import Radium from 'radium'

import Paper from 'material-ui/Paper'
import PaperBadge from 'components/PaperBadge'

import Door from './Door'
import Alarm from './Alarm'
import Keypad from './Keypad'

const styles = {
  wrapper: {
    display: 'flex',
    margin: -10,
  },
  paper: {
    height: 225,
    flex: 1,
    margin: 10,
    position: 'relative',
    padding: 20,
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div>
        <div style={styles.wrapper}>
          <Paper style={styles.paper} zDepth={1}>
            <PaperBadge title="Open" color="red" />
            <Door />
          </Paper>
          <Paper style={styles.paper} zDepth={1}>
            <Alarm />
          </Paper>
          <Paper style={styles.paper} zDepth={1}>
            <Keypad />
          </Paper>
        </div>
      </div>
    )
  }
}

export default Radium(Dashboard)
