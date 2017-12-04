import React, { Component } from 'react'
import Radium from 'radium'

import Paper from 'material-ui/Paper'
import { Tabs, Tab } from 'material-ui/Tabs'

import Logger from '../Logger'
import Keypad from '../Keypad'

const styles = {
  root: {
    marginLeft: 25,
    flex: 3,
  },
  tabsContainer: {
    backgroundColor: 'none',
  },
  tabBtn: {
    color: '#333',
  },
}

class Featured extends Component {
  state = {}

  render() {
    return (
      <Paper style={styles.root}>
        <Tabs
          tabItemContainerStyle={styles.tabsContainer}
        >
          <Tab buttonStyle={styles.tabBtn} label="Logs">
            <Logger logs={this.props.logs} />
          </Tab>
          <Tab buttonStyle={styles.tabBtn} label="Configuration">
            <Keypad />
          </Tab>
        </Tabs>
      </Paper>
    )
  }
}

Featured.defaultProps = {}

export default Radium(Featured)
