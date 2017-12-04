import React, { Component } from 'react'
import Radium from 'radium'

import socket from 'utils/socket'
import Paper from 'material-ui/Paper'
import { Tabs, Tab } from 'material-ui/Tabs'

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
  state = {
    logIntervalID: null,
  }

  componentDidMount = () => {
    if (!this.state.logIntervalID) {
      const logIntervalID = setInterval(() => {
        socket.emit('prime', 'help')
      }, 1000)

      this.setState({
        logIntervalID,
      })
    }

    socket.on('default', res => console.log(`result: ${res}`))
  }

  componentWillUnmount = () => {
    clearInterval(this.state.logIntervalID)
  }

  render() {
    return (
      <Paper style={styles.root}>
        <Tabs
          tabItemContainerStyle={styles.tabsContainer}
        >
          <Tab buttonStyle={styles.tabBtn} label="Logs">Logs</Tab>
          <Tab buttonStyle={styles.tabBtn} label="Analytics">Analytics</Tab>
        </Tabs>
      </Paper>
    )
  }
}

Featured.defaultProps = {}

export default Radium(Featured)
