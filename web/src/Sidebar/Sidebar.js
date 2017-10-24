import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import Navbar from 'components/Navbar'
import List from './List'

const styles = {
  root: {
    flex: 4,
    backgroundColor: '#20222D',
  },
  navbarRoot: {
    backgroundColor: '#a48ad4',
  },
  title: {
    fontSize: 18,
  },
}

class Sidebar extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Navbar
          title="Team Phílos"
          rootStyles={styles.navbarRoot}
          titleStyles={styles.title}
        />
        <List />
      </div>
    )
  }
}

Sidebar.propTypes = {}
Sidebar.defaultProps = {}

export default Radium(Sidebar)
