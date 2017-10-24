import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'
import { Chrome, Box, Activity, Server } from 'react-feather'

import ListItem from './ListItem'

const styles = {
  labelStyle: {
    color: '#9a9aa2',
  },
}

const List = props => (
  <div>
    <ListItem
      label="DASHBOARD"
      avatar={
        <Chrome color="#9a9aa2" size={30} />
      }
      labelStyle={styles.labelStyle}
    />
    <ListItem
      label="AUTOMATION"
      avatar={
        <Box color="#9a9aa2" size={30} />
      }
      labelStyle={styles.labelStyle}
    />
    <ListItem
      label="ANALYTICS"
      avatar={
        <Activity color="#9a9aa2" size={30} />
      }
      labelStyle={styles.labelStyle}
    />
    <ListItem
      label="SERVER DATA"
      avatar={
        <Server color="#9a9aa2" size={30} />
      }
      labelStyle={styles.labelStyle}
    />
  </div>
)

List.propTypes = {}
List.defaultProps = {}

export default Radium(List)
