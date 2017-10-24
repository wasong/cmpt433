import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import Navbar from 'components/Navbar'
import Avatar from 'material-ui/Avatar'

import List from './List'

const styles = {
  root: {
    flex: 4,
    backgroundColor: '#20222D',
  },
  navbarRoot: {
    padding: '0 20px',
    backgroundColor: '#a48ad4',
  },
  title: {
    color: '#fff',
    fontWeight: 'bold',
    fontSize: 18,
  },
  avatar: {
    margin: '0 10px 0 0',
  },
}

class Sidebar extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Navbar
          title="Team Phílos"
          icon={<Avatar src={null} style={styles.avatar} />}
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
