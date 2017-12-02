import React, { Component } from 'react'
import Radium from 'radium'

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
  state = {}

  render() {
    return (
      <Paper style={styles.root}>
        <Tabs
          tabItemContainerStyle={styles.tabsContainer}
        >
          <Tab buttonStyle={styles.tabBtn} label="Analytics">Analytics</Tab>
          <Tab buttonStyle={styles.tabBtn} label="Logs">Logs</Tab>
        </Tabs>
      </Paper>
    )
  }
}

Featured.defaultProps = {}

export default Radium(Featured)
